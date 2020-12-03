import java.io.FileNotFoundException;

public class main {
    public static int countTrees(Map map, int xStep, int yStep) {
        int x=0;
        int y=0;
    
        int treeCount = 0;
        while (y < map.getHeight()) {
            if (map.at(x, y) == Field.TREE) {
                treeCount += 1;
            } 
            x += xStep;
            y += yStep;
        }
        return treeCount;
    }

    public static void main(String []args) throws FileNotFoundException {
        Map map = new Map("input");
        
        int prod = 1;
        prod *= countTrees(map, 1, 1);
        prod *= countTrees(map, 3, 1);
        prod *= countTrees(map, 5, 1);
        prod *= countTrees(map, 7, 1);
        prod *= countTrees(map, 1, 2);

        System.out.println(prod);
    }
}
