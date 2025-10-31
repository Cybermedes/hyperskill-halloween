import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {

    public static String readFile() {
        String filename = "hyperskill-dataset-117428238.txt";
        Path filepath = Path.of(filename);

        try (BufferedReader br = Files.newBufferedReader(filepath)) {
            return br.readLine().trim();
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return "";
        }
    }

    public static void main(String[] args) {
        String sequence = readFile();
        Map<Character, Integer> digitFrequency = new HashMap<>();

        // Count the frequency of each digit
        for (char digit : sequence.toCharArray()) {
            digitFrequency.put(digit, digitFrequency.getOrDefault(digit, 0) + 1);
        }

        // Create modifiable list of Map entries
        List<Map.Entry<Character, Integer>> sorted = new ArrayList<>(digitFrequency.entrySet()
                .stream()
                .sorted(Map.Entry.comparingByValue((a, b) -> b.compareTo(a)))
                .toList());

        // If there are equal number of appearances, higher digit should come first
        for (int i = 0; i < sorted.size() - 1; i++) {
            if (sorted.get(i).getValue() == sorted.get(i + 1).getValue()
                    && sorted.get(i).getKey() < sorted.get(i + 1).getKey()) {
                Collections.swap(sorted, i, i + 1);
            }
        }

        System.out.println("Result: ");
        for (int i = 0; i < 4; i++) {
            System.out.print(sorted.get(i).getKey());
        }
        System.out.println();
    }
}
