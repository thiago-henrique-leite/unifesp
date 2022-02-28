package JavaProjects.figuras_geometricas;

public class Circulo extends Figura {
	private double raio;
	
	public Circulo(double raio) {
		setRaio(raio);
		setArea();
	}

	public double getRaio() {
		return raio;
	}

	public void setRaio(double raio) {
		this.raio = raio;
	}
	
	public void setArea() {
		this.area = 3.14 * (Math.pow(raio, 2));
	}
	
	public String toString() {
		return super.toString() + " - Raio: " + raio + "cm";
	}
}