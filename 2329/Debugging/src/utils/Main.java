package utils;

public class Main {
//		public static int greatestCommonFactor(int m, int n) {
//		    while (n != 0) {
//		        int temp = n;
//		        n = m % n;
//		        m = temp;
//		    }
//		    return m;
//		}
	
	public static int greatestCommonFactor(int m, int n) {
	    if (m < 0) {
	        m = -m;
	    }
	    if (n < 0) {
	        n = -n;
	    }

	    if (m == 0) {
	        return n;
	    }
	    if (n == 0) {
	        return m;
	    }

	    // Find the smaller number 
	    int limit = (m < n) ? m : n; 

	    // Find the GCF by checking divisors
	    int gcf = 1; // Initialize GCF
	    for (int i = 1; i <= limit; i++) {
	        if (m % i == 0 && n % i == 0) {
	            gcf = i; // Update GCF
	        }
	    }
	    return gcf;
	}

		public static void main(String[] args) {
		    System.out.println("gcf(3, 3) => " + greatestCommonFactor(3, 3));  // Output: 3
		    System.out.println("gcf(-1, 1) => " + greatestCommonFactor(-1, 1)); // Output: 1
		    System.out.println("gcf(0, 10) => " + greatestCommonFactor(0, 10)); // Output: 10

		    System.out.println("gcf(5, -10) => " + greatestCommonFactor(5, -10)); // Output: 10
		}

	

}
