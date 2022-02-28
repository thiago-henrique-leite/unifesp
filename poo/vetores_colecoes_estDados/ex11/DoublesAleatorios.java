package JavaProjects.vetores_colecoes_estDados.ex11;

//Crie uma classe que gera um vetor de doubles aleatórios. O construtor da classe deve receber
//um inteiro que corresponde ao tamanho do vetor.

public class DoublesAleatorios {
	private int length;
	private double[] array;
	
	public DoublesAleatorios(int length) {
		setLength(length);
		create_array();
	}

	public int getLength() {
		return length;
	}

	public void setLength(int length) {
		this.length = length;
	}
	
	public double[] getArray() {
		return array;
	}

	public void setArray(double[] array) {
		this.array = array;
	}
	
	private void create_array() {
		this.array = new double[length];
		
		for(int i=0; i<length; i++) {
			array[i] = (Math.random()*100) * Math.random();
		}
	}
	
	public void print() {
		for(int i=0; i<length; i++) {
			System.out.print(array[i]);
			System.out.print(" -> ");
		}
		System.out.println("null\n");
	}
	
	public static void main(String args[]) {
		DoublesAleatorios vet1 = new DoublesAleatorios(5);
		DoublesAleatorios vet2 = new DoublesAleatorios(9);
		
		vet1.print();
		vet2.print();
	}
}
