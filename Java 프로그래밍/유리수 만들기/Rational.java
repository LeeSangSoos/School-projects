package practice5;
import practice5.Creator;

public class Rational extends Number implements Creator {
	private long numerator = 0;
	private long denominator = 1;
	public Rational() {System.out.println("0");}
	public Rational(long numerator, long denominator) {
		long gcd = gcd(numerator, denominator);
		this.numerator=((denominator>0)? 1:-1)*numerator/gcd;
		this.denominator=Math.abs(denominator)/gcd;
		
	} 

	private static long gcd(long n, long d) { 
		while(d!=0) {
			long temp=n%d;
			n=d;
			d=temp;
		}
		return (n);
	} 

	public long getNumerator() { return numerator;}
	public long getDenominator() { return denominator;}
	public Rational add (Rational secondRational) { 
		long n = (numerator * secondRational.getDenominator()+
				denominator*secondRational.getNumerator());
		long d = denominator*secondRational.getDenominator();
		return new Rational(n, d);
	} 
	public Rational subtract(Rational secondRational) {
		long n = (numerator * secondRational.getDenominator()-
				denominator*secondRational.getNumerator());
		long d = denominator*secondRational.getDenominator();
		return new Rational(n, d);
	} 
	public Rational multiply(Rational secondRational) { 
		long n = numerator *secondRational.getNumerator();
		long d = denominator*secondRational.getDenominator();
		return new Rational(n, d);
	} 
	public Rational divide(Rational secondRational) { 
		long n = numerator*secondRational.getDenominator();
		long d = denominator*secondRational.getNumerator();
		return new Rational(n, d);
	}
	public String toString() { 
		String s= new String(numerator+"/"+denominator);
		long n = this.numerator;
		long d = this.denominator;
	    if (n == 0)
	    	s="0";
	    if (d==0)
	    	s="Error";
	    if (d==1)
	    	s=Long.toString(numerator);
	    if(d<0) {
	    	n=numerator*(-1);
	    	d=denominator*(-1);
	    	s=Long.toString(n/d);
	    }
	    	return s;
	}
	@Override
	public boolean equals (Object other ) { 
		if((this.toString()).equals(other))
			return true;
		return false;
	}
	@Override
	public int intValue() { 
		long l=numerator/denominator;
		int n=(int) l;
		return n;
	}
	@Override
	public float floatValue() { 
		float d=(float) denominator;
		float n=(float) numerator;
		return n/d;
	}	
	@Override
	public double doubleValue() { 
		double d=(double) denominator;
		double n=(double) numerator;
		return n/d;
	}
	@Override
	public long longValue() { 
		return numerator/denominator;
	}
	@Override 
	public void CreatorOfThisClass() {
		System.out.println("Creator of this class is Lee Sang Soo");
	}
}