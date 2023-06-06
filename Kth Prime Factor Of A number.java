// "static void main" must be defined in a public class.
public class Main {
    public static void main(String[] args) {
        
        // input 
        Scanner scn = new Scanner(System.in);
        int n = scn.nextInt();
        int k = scn.nextInt();
        
        //ALgo 
        int num = n;
        int ans = 0;
        boolean ansFound = false;
        int primeFactorCount = 0;
        
        // while the number is even, its only prime factor is 2
        while(num % 2 == 0){
            if(++primeFactorCount == k){// kth prime factor found
                ans = 2;
                ansFound = true;
                break;
            }
            num /= 2 ;// div num by 2
        }
        
        if(ansFound){
            System.out.println("Result : " + ans);
            return;
        }
        
        // reached here means numebr has now become odd (factors can be 2, 5, 7...n)
        for(int i=3; i <= num; i++){
            // if num is completely div by i, then divide it
            while(num % i == 0){
                if(++primeFactorCount == k){// kth prime factor found
                    ans = i;
                    ansFound = true;
                    break;
                }
                num /= i ;// div num by 2
            }
        }
        
        if(ansFound){
            System.out.println("Result : " + ans);
            return;
        }
        else System.out.println("No result found");
        
    }
}
