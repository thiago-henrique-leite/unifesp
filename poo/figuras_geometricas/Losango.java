package JavaProjects.figuras_geometricas;

public class Losango extends Paralelogramo {
	public Losango(double diagonalMaior, double diagonalMenor) {
		super(diagonalMaior, diagonalMenor);
		setArea();
	}

	public void setArea() {
		this.area = ( a*b / 2);
	}
	
	public String toString() {
		return this.getClass().getSimpleName() + " - Área: " + getArea() + "cm²"
				+ " - Diagonal A: " + a + "cm" + " - Diagonal B: " + b + "cm";
	}
}