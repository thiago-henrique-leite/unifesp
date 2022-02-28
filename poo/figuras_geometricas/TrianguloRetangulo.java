package JavaProjects.figuras_geometricas;

public class TrianguloRetangulo extends Triangulo {	
	public TrianguloRetangulo(int base, int altura, int hipotenusa) {
		super(base, altura, hipotenusa);
		setArea();
	}
	
	public void setArea() {
		// Encontra os dois menores valores, referentes a base e altura
		// Define a área do triângulo retângulo dada por ( Base * Altura / 2)
		
		if(b<=a && c<=a)
			this.area = b*c / 2;
		else {
			if(a<=b && c<=b)
				this.area = a*c / 2;
			else 
				this.area = a*b / 2;
		}
	}
	
	public String toString() {
		return super.toString();
	}
}