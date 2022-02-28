package JavaProjects.interfaces.Relacao;

public class ParOrdenado {
	private double x, y;
	
	public ParOrdenado(double x, double y) {
		setX(x); setY(y);
	}
	
	public void setX(double value) { this.x = value; }
	public void setY(double value) { this.y = value; }
	
	public double getX() { return this.x; }
	public double getY() { return this.y; }
}