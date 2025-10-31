import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {

    public static String readFile() {
        String filename = "hyperskill-dataset-117458807.txt";
        Path filepath = Path.of(filename);

        try {
            return Files.readString(filepath).trim();
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return "";
        }
    }

    // 1,11001010001001111000111011001100
    public static void main(String[] args) {
        long phoneNumber = Long.parseLong(readFile());
        long uintMax = ((long) Integer.MAX_VALUE) * 2 + 2; // Exercise considers 2^32 not 2^32-1
        System.out.println(uintMax);
        int overflows = 0;

        while (phoneNumber >= uintMax) {
            phoneNumber -= uintMax;
            overflows++;
        }

        String binaryPhoneNumber = Long.toBinaryString(phoneNumber);

        System.out.printf("%d,%s\n", overflows, binaryPhoneNumber);
    }
}
