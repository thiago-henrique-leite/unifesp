package JavaProjects.class_abstract_robo;

public abstract class RoboAbstrato {
	protected String nome;
	protected int posicaoXAtual;
	protected int posicaoYAtual;
	protected short direcao;
	
	public RoboAbstrato(String n, int px, int py, short d) {
		nome = n;
		posicaoXAtual = px;
		posicaoYAtual = py;
		direcao = d;
	}
	
	public void move() {
		move(1);	
	}
	
	public abstract void move(int passos);
	
	public void moveX(int passos) {
		posicaoXAtual += passos;
	}
	
	public void moveY(int passos) {
		posicaoYAtual += passos;
	}
	
	public void mudaDirecao(short novaDir) {
		direcao = novaDir;
	}
	
	public short direcaoAtual() {
		return direcao;
	}
	
	public String toString() {
		String resultado = "Nome do robô:" + nome + "\n";
		resultado = resultado + "Posição do robô: (" + posicaoXAtual + ","
		+ posicaoYAtual + ")\n";
		resultado = resultado + "Direção do robô:" + direcao;
		return resultado;
  }
}