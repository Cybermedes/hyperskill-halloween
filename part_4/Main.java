import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static final char[][] KEYPAD = {
            { 'A', 'B', 'C', 'D' },
            { 'E', 'F', 'G', 'H' },
            { 'I', 'J', 'K', 'L' },
            { 'M', 'N', 'O', 'P' }
    };

    public static List<String> readFile() {
        Path filepath = Path.of("hyperskill-dataset-117566097.txt");
        List<String> lines = new ArrayList<>();

        // Read all file lines, including the last empty line
        try (RandomAccessFile raf = new RandomAccessFile(filepath.toFile(), "r")) {
            lines.addAll(Files.readAllLines(filepath));

            // Check if there is an empty last line
            if (raf.length() > 0) {
                raf.seek(raf.length() - 1);
                if (raf.read() == '\n' || raf.read() == '\r') {
                    lines.add("");
                }
            }

            return lines;

        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public static char getLetterFromKeypad(String directions) {
        int y = 0, x = 0;

        for (String direction : directions.split("\\,")) {
            switch (direction) {
                case "UP" -> {
                    if (y > 0) {
                        y -= 1;
                    }
                }
                case "DOWN" -> {
                    if (y < 3) {
                        y += 1;
                    }
                }
                case "RIGHT" -> {
                    if (x < 3) {
                        x += 1;
                    }
                }
                case "LEFT" -> {
                    if (x > 0) {
                        x -= 1;
                    }
                }
            }
        }

        return KEYPAD[y][x];
    }

    public static void main(String[] args) {
        List<String> sequence = readFile();
        StringBuilder sb = new StringBuilder();

        for (String directions : sequence) {
            sb.append(getLetterFromKeypad(directions));
        }
        
        System.out.println(sb);
    }
}
