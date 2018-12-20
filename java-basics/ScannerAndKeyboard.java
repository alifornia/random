import java.util.Scanner;

public class ScannerAndKeyboard
{
	private final double q;
	public ScannerAndKeyboard(double i_q){
		q = i_q;
	}
	public static double harmonic(int n){
		double sum =0.0;
		for(int i =1; i <=n; i++){
			sum += 1.0/i;
		}
		return sum;
	}
	public String to_String(String [] sss){
		return "AAA";
	}

	public static void main(String[] args)
	{	Scanner s = new Scanner(System.in);
		System.out.print( "Enter your name: "  );
		String name = s.nextLine();
		System.out.println( "Hello " + name + "!" );

		byte zero = 0;
        String output = "W" + zero + "w";
        System.out.println(output);

		String a = new String("Wow");
        String b = "Wow";
        String c = a;
        String d = c;


		boolean b1 = a == b;
        boolean b2 = b.equals(b + "!");
        boolean b3 = !c.equals(a);

        if (b1 && b2 && b3) {
            System.out.println("Success!");
        }

        int[] numbers = {1, 2, 3};
        int length = numbers[2];
        char[] chars = new char[length];
        chars[numbers.length-1] = 'y';
        System.out.println("Done!");

			double ss = harmonic(10);
			System.out.println(ss);
		ScannerAndKeyboard SAK = new ScannerAndKeyboard(3.4);
		System.out.println(2.0*SAK.q);

		int[][] matrix = { { 1, 2, 3 }, { 4, 5, 6 } };
		for (int[] array: matrix) {
    		for (int number: array) {
         		System.out.println(number);
			}
		}
	}


}