using System;
using System.IO;

public class HelloWorld
{
    public static void Main(string[] args)
    {
        var lines = File.ReadAllLines("input");
        var ids = new int[lines.Length];

        for (var i=0; i<lines.Length; ++i) {
            int val = 0;
            foreach (var c in lines[i]) {
                val *= 2;
                if (c == 'B' || c == 'R') {
                    val += 1; 
                }
            }
            ids[i] = val;
        }

        Array.Sort(ids);

        Console.WriteLine(ids[ids.Length - 1]);
        
        for (var i=1; i<ids.Length; ++i) {
            if (ids[i-1] + 1 != ids[i]) {
                Console.WriteLine(ids[i-1]+1);
            }
        }

    }
}
