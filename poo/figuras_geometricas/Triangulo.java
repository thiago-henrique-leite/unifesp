package JavaProjects.figuras_geometricas;

public class Triangulo extends Figura {
	protected int a, b, c;
	protected double perimetro;
	
	public Triangulo(int lado1, int lado2, int lado3) {
		setA(lado1);
		setB(lado2);
		setC(lado3);
		setArea();
	}
	
	public void setA(int valor) {
		a = valor;
	}
	
	public void setB(int valor) {
		b = valor;
	}

	public void setC(int valor) {
		c = valor;
	}
	
	public void setPerimetro() {
		perimetro = a + b + c;
	}
	
	public double getPerimetro() {
		setPerimetro();
		return perimetro;
	}
	
	public void setArea() {
		// Formula de Heron
		double p = getPerimetro() / 2;
		
		this.area = Math.sqrt(p * (p-a) * (p-b) * (p-c));
	}
	
	public boolean validaTriangulo(int x, int y, int z) {
		int xy, xz, yz;
		
		xy = x + y;
		xz = x + z;
		yz = y + z;
				
		return (xy > z && xz > y && yz > x) ? true : false;
	}
	
	public String toString() {
		return super.toString() + " - Lado A: " + a + "cm" + " - Lado B: " + b 
				+ "cm" + " - Lado C: " + c + "cm";
	}
}