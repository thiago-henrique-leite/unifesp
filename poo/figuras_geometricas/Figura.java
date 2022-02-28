package JavaProjects.figuras_geometricas;

public class Figura {
	protected double area;
	
	protected double getArea() {
		return this.area;
	}

	public String toString() {
		return this.getClass().getSimpleName() + " - Área: " + getArea() + "cm²";
	}
}