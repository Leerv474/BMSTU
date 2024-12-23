package bmstu.lab.task1;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Runner {
    public void start() throws InterruptedException {
        int[] array = generateLargeArray(1_000_000);
        int numberOfThreads = 8;

        int chunkSize = (int) Math.ceil((double) array.length / numberOfThreads);
        List<Thread> threads = new ArrayList<>();
        List<MaxSearch> searches = new ArrayList<>();

        for (int i = 0; i < numberOfThreads; i++) {
            int start = i * chunkSize;
            int end = Math.min(start + chunkSize, array.length);

            MaxSearch search = new MaxSearch(array, start, end);
            Thread thread = new Thread(search);
            searches.add(search);
            threads.add(thread);
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }

        int globalMax = Integer.MIN_VALUE;
        for (MaxSearch search : searches) {
            globalMax = Math.max(globalMax, search.getResult());
        }

        System.out.println("Maximum value: " + globalMax);
    }

    private static int[] generateLargeArray(int size) {
        Random random = new Random();
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt(1_000_000);
        }
        return array;
    }
}
