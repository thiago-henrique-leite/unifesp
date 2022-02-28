package JavaProjects.mortal;

public class Contador {
	private int valor;
	
	public Contador() {
		zera();
	}
	
	public void setValor(int valor) {
		this.valor = valor;
	}
	
	public int getValor() {
		return valor;
	}

	public void incrementa() {
		this.valor += 1;
	}
	
	public void decrementa() {
		this.valor -= 1;
	}
	
	public void zera() {
		setValor(0);
	}
}