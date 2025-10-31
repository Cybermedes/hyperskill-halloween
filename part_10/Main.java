import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class Main {

    public static List<String> readFile() {
        String filename = "hyperskill-dataset-117527537.txt";
        Path filepath = Path.of(filename);

        try {
            return Files.readAllLines(filepath);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public static void main(String[] args) {
        List<String> sequence = readFile();
        Map<Character, Integer> frequency = new LinkedHashMap<>();
        StringBuilder sb = new StringBuilder();

        for (String line : sequence) {
            // Get the frequency of each letter
            for (char ch : line.trim().toCharArray()) {
                frequency.put(ch, frequency.getOrDefault(ch, 0) + 1);
            }

            // Get the unique letters
            for (Map.Entry<Character, Integer> entry : frequency.entrySet()) {
                if (entry.getValue() == 1) {
                    sb.append(entry.getKey());
                }
            }

            frequency.clear(); // Clear Map for another iteration
        }

        System.out.println(sb);
    }
}
