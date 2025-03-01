package exam;

public class Exam 
{
    public static void main(String[] args) 
    {
        System.out.println("Hello");
        int i = 0;
        while (i < 1000000) 
        {
        	if (i == 15863) {
        	
        	 System.out.println("i = " + i);
        	}
            if (i % 10 == 2) 
            {
                System.out.println("i = " + i);
            } 
            else if (i % 10 == 6)
            {
                System.out.println("i = " + i);
            } 
            else if (i % 2 == 0) 
            {
                System.out.println("i = " + i);
            }
            i++;
        }
    }
}