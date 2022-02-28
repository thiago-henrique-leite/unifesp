package JavaProjects.mortal;

public class Mortal {
	private boolean vivo;
	private String name;
	
	public Mortal(String name) {
		setName(name);
		setVivo(true);
	}
	
	public void setVivo(boolean state) {
		this.vivo = state;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public boolean isVivo() {
		return this.vivo;
	}
	
	public void mata() {
		System.out.printf("\nMortal.mata()");
		setVivo(false);
	}
	
	public String toString() {
		return this.getClass().getSimpleName() 
				+ " - Nome: " + Mortal.this.getName() 
				+ " - Está vivo? " + Mortal.this.isVivo();
	}
}