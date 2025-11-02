import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

public class Part9 {

    public static class Node {
        int y, x;
        String path;

        Node(int y, int x, String path) {
            this.y = y;
            this.x = x;
            this.path = path;
        }
    }

    public static List<String> readFile() {
        String filename = "hyperskill-dataset-117515174.txt";
        Path filepath = Path.of(filename);

        try {
            return Files.readAllLines(filepath);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public static void main(String[] args) {
        
        List<String> lines = readFile();
        
        // Convert to 2D char array
        char[][] maze = new char[lines.size()][lines.get(0).length()];
        int startY = 0, startX = 0, garageY = 0, garageX = 0;

        // Get coordinates of player and garage
        for (int y = 0; y < lines.size(); y++) {
            for (int x = 0; x < lines.get(y).length(); x++) {
                maze[y][x] = lines.get(y).charAt(x);
                if (maze[y][x] == 'P') {
                    startY = y;
                    startX = x;
                }
                if (maze[y][x] == 'G') {
                    garageY = y;
                    garageX = x;
                }
            }
        }

        String shortestPath = bfs(maze, startY, startX, garageY, garageX);
        if (shortestPath != null) {
            System.out.println("Shortest Path: " + shortestPath);
        } else {
            System.out.println("No path found!");
        }
    }

    // Breadth-First Search Algorithm
    private static String bfs(char[][] maze, int sy, int sx, int gy, int gx) {

        int rows = maze.length, cols = maze[0].length;
        boolean[][] visited = new boolean[rows][cols];

        // Directions: U, D, L, R
        int[] dy = { -1, 1, 0, 0 };
        int[] dx = { 0, 0, -1, 1 };
        char[] dir = { 'U', 'D', 'L', 'R' };

        Queue<Node> queue = new LinkedList<>();
        queue.add(new Node(sy, sx, ""));
        visited[sy][sx] = true;

        while (!queue.isEmpty()) {
            Node current = queue.poll();

            if (current.y == gy && current.x == gx) {
                return current.path; // found garage
            }

            for (int i = 0; i < 4; i++) {
                int ny = current.y + dy[i];
                int nx = current.x + dx[i];

                if (ny >= 0 && ny < rows && nx >= 0 && nx < cols &&
                        maze[ny][nx] != '#' && !visited[ny][nx]) {
                    visited[ny][nx] = true;
                    queue.add(new Node(ny, nx, current.path + dir[i]));
                }
            }
        }

        return null; // no path found
    }
}
