
import java.util.ArrayList;
import java.util.List;

class KMP{
    
    String pattern;
    int[] LPSTable; // table[i] stores length of longest prefix suffix of string[0:i]

    public KMP(String pattern){
        this.pattern = pattern;
        this.LPSTable = buildLPSTable();
    }

    private int[] buildLPSTable(){
        int[] LPSTable = new int[pattern.length()];
        LPSTable[0] = 0; // length of LPS for string of length 1 is 0, because in LPS including self is not allowed
        int i=1;
        int len=0; // stores length of LPS till now 
        while(i < pattern.length()){
            if(pattern.charAt(len) == pattern.charAt(i)){
                len++;
                LPSTable[i] = len;
                i++;
            }
            else{
                if(len > 0){ // shrink
                    len = LPSTable[len-1]; // we do not increment i here coz we only shifting the left end for comparing (i.e len) not the right end i.e i
                }else{
                    LPSTable[i] = 0;
                    i++;
                }
            }
        }
        return LPSTable;
    }

    public int[] search(String text, String pattern){

        int i=0, j=0;
        List<Integer> resultIndices = new ArrayList<>();
        while(i < text.length()){
            if(text.charAt(i) == pattern.charAt(j)){
                i++;
                j++;
            }
            if(j == pattern.length()){
                // System.out.println("Pattern found at index " + (i-j));// subtraced j coz i reached end of the pattern so start of pattern is j steps behind i
                resultIndices.add(i-j);
                j = LPSTable[j - 1]; // Continue searching for next match, as there can be more, using table so we do not have to start from 0 again
            }
            else if(i < text.length() && text.charAt(i) != pattern.charAt(j)){
                if(j != 0){
                    j = LPSTable[j - 1]; // intellijenty jump back j pointer to few position back, using LPS table as there can be a smaller LPS present in left end
                }
                else{// using table we walked backward to the left end of the pattern, can't move j more, so move i instead
                    i++;
                }
            }
        }

        return resultIndices.stream().mapToInt(Integer::intValue).toArray();
        
    }


}

public class KnuthMorrisPrattAlgo {

    public static void main(String[] args){

        // test case 1 : output index 10 
        String text = "ABABDABACDABABCABAB";
        String pattern = "ABABCABAB";

        KMP kmp = new KMP(pattern);

        int[] resultIndices = kmp.search(text, pattern);
        for(int i:resultIndices){
            System.out.println("pattern present at index : " + i);
        }

        // test case 2 :  output : 0,1,2,3
        String text2 = "AAAAA";
        String pattern2 = "AA";

        KMP kmp2 = new KMP(pattern2);

        int[] resultIndices2 = kmp2.search(text2, pattern2);
        for(int i:resultIndices2){
            System.out.println("pattern present at index : " + i);
        }

        System.out.println();
    }
}