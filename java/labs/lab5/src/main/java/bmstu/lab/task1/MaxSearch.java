package bmstu.lab.task1;

public class MaxSearch implements Runnable {
    private final int[] array;
    private final int start;
    private final int end;
    private int result;

    public int getResult() {
        return this.result;
    }

    public MaxSearch(int[] array, int start, int end) {
        this.array = array;
        this.start = start;
        this.end = end;
    }

    @Override
    public void run() {
        int max = Integer.MIN_VALUE;
        for (int i = start; i < end; i++) {
            max = Math.max(max, array[i]);
        }
        result = max;
    }
}


