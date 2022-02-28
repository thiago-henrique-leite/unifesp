package JavaProjects.figuras_geometricas;

public class Main extends Figura {
	public static void main(String args[]) {
		Circulo cir = new Circulo(5);
		Losango los = new Losango(6, 9);
		Paralelogramo par = new Paralelogramo(16, 23);
		Quadrado qua = new Quadrado(17);
		Retangulo ret = new Retangulo(69, 36);
		Triangulo tri = new Triangulo(15, 20, 7);
		TrianguloRetangulo tri_ret = new TrianguloRetangulo(3, 4, 5);
		
		System.out.println(cir.toString() + "\n");
		System.out.println(los.toString() + "\n");
		System.out.println(par.toString() + "\n");
		System.out.println(qua.toString() + "\n");
		System.out.println(ret.toString() + "\n");
		System.out.println(tri.toString() + "\n");
		System.out.println(tri_ret.toString());
	}
}