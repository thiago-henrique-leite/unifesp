package JavaProjects.exceptions.ex2.org;

public class MyException extends Exception {
	private static final long serialVersionUID = 1L;
	private String message;
	
	public MyException() {};
	
	public MyException(String message) {
		super(message);
		setMessage(message);
	}
	
	public MyException(String message, Throwable cause) {
		super(message, cause);
		setMessage(message);
	}
	
	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}
	
	public static void main(String args[]) {
		try {
			throw new MyException("Erro capturado!");
		} catch (MyException e) {
			System.err.println(e.getMessage());
		} finally {
			System.out.println("Nova exceção criada com sucesso!");
		}
	}
}
