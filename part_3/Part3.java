import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Map.Entry;

public class Part3 {

	public static String readFile() {
		Path filepath = Path.of("hyperskill-dataset-117460572.txt");

		try (BufferedReader br = Files.newBufferedReader(filepath)) {
			return br.readLine().trim();
		} catch (IOException e) {
			System.err.println("Error: " + e.getMessage());
			return "";
		}
	}

	public static void main(String[] args) {
		String sequence = readFile();

		// Use LinkedHashMap to add elements at their order of insertion
		Map<Character, Integer> frequency = new LinkedHashMap<>();

		for (char letter : sequence.toCharArray()) {
			frequency.put(letter, frequency.getOrDefault(letter, 0) + 1);
		}

		System.out.print("Result: ");
		for (Entry<Character, Integer> entry : frequency.entrySet()) {
			if (entry.getValue() == 1) {
				System.out.print(entry.getKey());
			}
		}
		System.out.println();
	}
}
