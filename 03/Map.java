import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

enum Field {TREE, EMPTY};

public class Map {
    Map(String fileName) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(fileName));
        this.fields = new ArrayList<ArrayList<Field>>();

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            ArrayList<Field> lineList = new ArrayList<Field>();
            for (int c=0; c<line.length(); ++c) {
                lineList.add(line.charAt(c) == '#' ? Field.TREE : Field.EMPTY);
            } 

            fields.add(lineList);
        }            
    }  

    Field at(int x, int y) {
        ArrayList<Field> line = fields.get(y);
        return line.get(x % line.size());
    }

    int getHeight() {
        return fields.size();
    }

    private ArrayList<ArrayList<Field>> fields;
};
