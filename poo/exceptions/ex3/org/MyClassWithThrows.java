package JavaProjects.exceptions.ex3.org;

public class MyClassWithThrows {
	public static void throwsMyException(String message) throws MyException {
		throw new MyException(message);
	}
	
	public static void main(String args[]) {
		try {
			throwsMyException("My Exception in MyClass");
		} catch(MyException e) {
			System.err.println(e.getMessage());
		}
	}
}
