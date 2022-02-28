package JavaProjects.figuras_geometricas;

public class Quadrado extends Figura {
	private double lado;
				
	public Quadrado(double lado) {
		setLado(lado);
		setArea();
	}
	
	public void setLado(double medida) {
		lado = medida;
	}
	
	public void setArea() {
		this.area = lado*lado;
	}
	
	public String toString() {
		return super.toString() + " - Lado: " + lado + "cm";
	}
}