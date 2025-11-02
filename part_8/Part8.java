import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;

public class Part8 {

    private static String readFile() {
        String filename = "hyperskill-dataset-117528132.txt";
        Path filepath = Path.of(filename);

        try (BufferedReader br = Files.newBufferedReader(filepath)) {
            return br.readLine().trim();
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return "";
        }
    }

    public static void main(String[] args) {

        List<String> words = Arrays.asList(readFile().split("\\s+"));

        // Find the first word that is NOT an anagram of any other
        String noAnagram = words.stream()
                .filter(word1 -> words.stream().noneMatch(word2 -> areRealAnagrams(word1, word2)))
                .findFirst()
                .orElse("No unique word found");

        System.out.println(noAnagram);
    }

    // Check if two words are real anagrams (same letters, not identical)
    private static boolean areRealAnagrams(String word1, String word2) {
        if (word1.length() != word2.length() || word1.equals(word2)) {
            return false;
        }

        int[] charCount = new int[26];
        for (int i = 0; i < word1.length(); i++) {
            charCount[word1.charAt(i) - 'a']++;
            charCount[word2.charAt(i) - 'a']--;
        }

        for (int count : charCount) {
            if (count != 0) {
                return false;
            }
        }
        return true;
    }
}
