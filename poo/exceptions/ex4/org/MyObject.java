package JavaProjects.exceptions.ex4.org;

public class MyObject {
	private String name;
	
	public MyObject(String name) {
		this.name = name;
	}
	
	public String getName() {
		return this.name;
	}
	
	@SuppressWarnings("null")
	public static void main(String args[]) {
		MyObject obj = null;
		
		try {
			obj.getName();
		} catch(NullPointerException e) {
			System.err.println("Erro capturado:");
			e.printStackTrace();
		}
	}
}
