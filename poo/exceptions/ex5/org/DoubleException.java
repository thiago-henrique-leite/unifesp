package JavaProjects.exceptions.ex5.org;

public class DoubleException {
	public static void g() throws MyException {
		throw new MyException("Primeira Exception!");
	}
	
	public static void f() throws Exception {
		try {
			g();
		} catch (MyException e) {
			System.err.println(e.getMessage() + "\n");
			throw new Exception("Segunda Exception!");
		}
	}
	
	public static void main(String args[]) throws Exception {
		f();
	}
}
