package JavaProjects.mortal;

public class Gato extends Mortal {
	private String breed;
	private Contador counter = new Contador();
	
	public Gato(String name, String breed) {
		super(name);
		setBreed(breed);
	}
	
	public void setBreed(String breed) {
		this.breed = breed;
	}
	
	public String getBreed() { return this.breed; }
	
	public void mata() {
		this.counter.incrementa();
				
		System.out.printf("\n%dx - Gato.mata()", counter.getValor());

		if(counter.getValor() == 7) {
			setVivo(false);
			this.counter.zera();
		}
	}
}