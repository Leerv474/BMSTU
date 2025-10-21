package com.example.lab8;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.BatteryManager;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;

public class BatteryMonitorService extends Service {

    private float maxDischargeRate = 2.0f;

    private float lastBatteryLevel = -1;
    private long lastTimeMillis = 0;

    private final Handler handler = new Handler();
    private final Runnable monitorTask = new Runnable() {
        @Override
        public void run() {
            checkBatteryStatus();
            handler.postDelayed(this, 60_000);
        }
    };

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (intent != null && intent.hasExtra("maxRate")) {
            maxDischargeRate = intent.getFloatExtra("maxRate", 2.0f);
        }

        createNotificationChannel();

        Notification notification = new NotificationCompat.Builder(this, "battery_alert")
                .setContentTitle("Battery Monitor Running")
                .setContentText("Monitoring discharge rate")
                .setSmallIcon(android.R.drawable.ic_menu_info_details)
                .build();

        startForeground(100, notification);

        handler.post(monitorTask);
        return START_STICKY;
    }

    private void createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel channel = new NotificationChannel(
                    "battery_alert",
                    "Battery Alerts",
                    NotificationManager.IMPORTANCE_HIGH
            );
            channel.setDescription("Notifications for battery discharge rate alerts");

            NotificationManager nm = getSystemService(NotificationManager.class);
            if (nm != null) {
                nm.createNotificationChannel(channel);
            }
        }
    }

    @Override
    public void onDestroy() {
        handler.removeCallbacks(monitorTask);
        super.onDestroy();
    }

    private void checkBatteryStatus() {
        IntentFilter ifilter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
        Intent batteryStatus = registerReceiver(null, ifilter);

        if (batteryStatus == null) {
            Log.w("BatteryService", "Battery status unavailable");
            return;
        }

        int level = batteryStatus.getIntExtra(BatteryManager.EXTRA_LEVEL, -1);
        int scale = batteryStatus.getIntExtra(BatteryManager.EXTRA_SCALE, -1);

        if (level < 0 || scale <= 0) {
            Log.w("BatteryService", "Invalid battery data");
            return;
        }

        float batteryPct = level * 100f / scale;

        long currentTime = System.currentTimeMillis();

        if (lastBatteryLevel >= 0) {
            float deltaLevel = lastBatteryLevel - batteryPct;
            float deltaTimeMinutes = (currentTime - lastTimeMillis) / 60000f;

            if (deltaTimeMinutes > 0) {
                float rate = deltaLevel / deltaTimeMinutes;
                Log.d("BatteryService", "Rate = " + rate + "%/min");

                if (rate > maxDischargeRate) {
                    sendNotification(rate);
                }
                updateNotification(rate, batteryPct);
            }
        }

        lastBatteryLevel = batteryPct;
        lastTimeMillis = currentTime;
    }

    private void updateNotification(float rate, float batteryPct) {
        String message = String.format(
                "Current: %.1f%% • Rate: %.2f%%/min • Limit: %.2f%%/min",
                batteryPct, rate, maxDischargeRate
        );

        boolean alert = rate > maxDischargeRate;

        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "battery_alert")
                .setContentTitle(alert ? "⚠️ High Discharge Rate!" : "Battery Monitor")
                .setContentText(message)
                .setPriority(NotificationCompat.PRIORITY_HIGH)
                .setSmallIcon(R.drawable.ic_launcher_foreground)
                .setOngoing(true);

        NotificationManager nm = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        nm.notify(1, builder.build());
    }

    private void sendNotification(float rate) {
        NotificationManager nm = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "battery_alert")
                .setContentTitle("⚠️ High Discharge Rate!")
                .setContentText(String.format("Current rate: %.2f %%/min * limit, %.2f%%/min", rate, maxDischargeRate))
                .setSmallIcon(R.drawable.ic_launcher_foreground)
                .setPriority(NotificationCompat.PRIORITY_HIGH);
        nm.notify(1, builder.build());
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}
