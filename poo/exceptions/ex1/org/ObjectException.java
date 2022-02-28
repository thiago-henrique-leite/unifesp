package JavaProjects.exceptions.ex1.org;

public class ObjectException {
	public static void main(String args[]) {
		try {
			throw new Exception("Erro!");
		} catch (Exception e) {
			System.err.println(e.getMessage());
		} finally {
			System.out.println("Passamos por aqui!");
		}
	}
}
