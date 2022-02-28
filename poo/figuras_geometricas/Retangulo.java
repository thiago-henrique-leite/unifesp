package JavaProjects.figuras_geometricas;

public class Retangulo extends Figura {
	private double base, altura;
	
	public Retangulo(double base, double altura) {
		setBase(base);
		setAltura(altura);
		setArea();
	}
	
	public void setBase(double medida) {
		base = medida;
	}
	
	public void setAltura(double medida) {
		altura = medida;
	}
	
	public void setArea() {
		this.area = base*altura;
	}
	
	public String toString() {
		return super.toString() + " - Base: " + base + "cm" + " - Altura: " + altura + "cm";
	}
}