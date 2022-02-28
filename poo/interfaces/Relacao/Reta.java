package JavaProjects.interfaces.Relacao;

public class Reta implements Relacao {
	private ParOrdenado p1, p2;
	
	public Reta(ParOrdenado a, ParOrdenado b) {
		setA(a); setB(b);
	}
	
	public void setA(ParOrdenado p) { this.p1 = p; }
	public void setB(ParOrdenado p) { this.p2 = p; }
	
	public ParOrdenado getA() { return this.p1; }
	public ParOrdenado getB() { return this.p2; }
	
	public double distancia() {
		return Math.sqrt(Math.pow((p2.getX() - p1.getX()), 2) + Math.pow((p2.getY() - p1.getY()), 2));
	}
	public boolean maiorQue(Object b) {
		return (distancia() > ((Reta) b).distancia()) ? true : false;
	}

	public boolean menorQue(Object b) {
		return (distancia() < ((Reta) b).distancia()) ? true : false;
	}

	public boolean igualA(Object b) {
		return (distancia() == ((Reta) b).distancia()) ? true : false;
	}
	
	public void print() {
		System.out.printf("A(%.0f, %.0f), B(%.0f, %.0f)\n", p1.getX(), p1.getY(), p2.getX(), p2.getY());
	}
	
	public static void printInfos(Reta reta1, Reta reta2) {
		System.out.printf("Reta1: ");
		reta1.print();
		System.out.printf("Reta2: ");
		reta2.print();
	
		System.out.printf("\nReta1 distância: %.2f\n", reta1.distancia());
		System.out.printf("Reta2 distância: %.2f\n", reta2.distancia());
		
		System.out.printf("\nReta1 maior que Reta2 ? %s\n", reta1.maiorQue(reta2));
		System.out.printf("Reta1 menor que Reta2 ? %s\n", reta1.menorQue(reta2));
		System.out.printf("Reta1 igual a Reta2 ? %s\n", reta1.igualA(reta2));
	}
	
	public static void main(String args[]) {		
		ParOrdenado p1, p2, p3, p4;
		
		p1 = new ParOrdenado(1, 1);
		p2 = new ParOrdenado(1, 4);
		
		p3 = new ParOrdenado(-2, 4);
		p4 = new ParOrdenado(2, 2);
		
		Reta reta1 = new Reta(p1, p2);
		Reta reta2 = new Reta(p3, p4);
		
		Reta.printInfos(reta1, reta2);
	}
}
