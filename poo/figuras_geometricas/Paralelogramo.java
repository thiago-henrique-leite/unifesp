package JavaProjects.figuras_geometricas;

public class Paralelogramo extends Figura {
	protected double a, b;
	
	public Paralelogramo(double base, double altura) {
		setA(altura);
		setB(base);
		setArea();
	}
	
	public void setA(double a) {
		this.a = a;
	}
	
	public void setB(double b) {
		this.b = b;
	}
	
	public void setArea() {
		this.area = a*b;
	}
	
	public String toString() {
		return super.toString() + " - Base: " + a + "cm" + " - Altura: " + b + "cm";
	}
}