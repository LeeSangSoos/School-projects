package practice5;
import practice5.Rational;
import practice5.Creator;

public class TestRational {

	public static void main(String[] args) {
		Rational r1= new Rational(4,2);
		Rational r2 = new Rational(2,3);
		System.out.println(r1+" + "+r2+" = "+r1.add(r2));
		System.out.println(r1+" - "+r2+" = "+r1.subtract(r2));
		System.out.println(r1+" * "+r2+" = "+r1.multiply(r2));
		System.out.println(r1+" / "+r2+" = "+r1.divide(r2));
		
		System.out.println(r2+" to int is "+r2.intValue());
		System.out.println(r2+" to double is "+r2.doubleValue());
		System.out.println(r2+" to float is "+r2.floatValue());
		System.out.println(r2+" to long is "+r2.longValue());
		
		if(r1.equals(r2))
			System.out.println("Two rational numbers are equal");
		else
			System.out.println("Two rational numbers are not equal");
		
		r1.CreatorOfThisClass();
		r2.CreatorOfThisClass();
		
	}

}
