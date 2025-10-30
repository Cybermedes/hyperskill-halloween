import java.nio.file.*;
import java.io.IOException;
import java.util.*;
import java.util.regex.Pattern;

public class Main {

    // Option 1: Hardcoded dataset
    private static final String DATASET = """
        dqmbghlnfrwu dnhguwmlqrbf wprzdiogcvbtajsqh nidhcrugka rpizgqcwtdsahovbj lyndwkjvote dyetvknojwl
    """.trim();

    public static void main(String[] args) throws IOException {
        // Option 2: Uncomment this if reading from file instead
        // Path pathDataSetDay8 = Paths.get("src/main/resources/hyperskill-dataset-day-8.txt");
        // String datasetFromFile = Files.readString(pathDataSetDay8);

        String datasetPlaygroundDay08 = DATASET;

        // Split dataset into individual words
        List<String> allWords = Arrays.asList(datasetPlaygroundDay08.split("\\s+"));

        // Find the first word that is NOT an anagram of any other
        String foundNameThatIsNoAnagram = allWords.stream()
            .filter(word1 -> allWords.stream().noneMatch(word2 -> areRealAnagrams(word1, word2)))
            .findFirst()
            .orElse("No unique word found");

        System.out.println(foundNameThatIsNoAnagram);
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
