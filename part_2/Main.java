import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {

	public static String readFile() {
		String filename = "hyperskill-dataset-117443619.txt";
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

		int deg = 0, result = 0;
		for (String degree : sequence.split("\\,")) {
			deg = Integer.parseInt(degree);

			result += deg;

			if (result > 360) {
				result -= 360;
			} else if (result < 0) {
				result += 360;
			}
		}

		System.out.println("Result: " + result);
	}
}
