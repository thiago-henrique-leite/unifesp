package JavaProjects.class_abstract_robo;

public class RoboQueDeveVoltar extends RoboAbstrato {
	private long energia;
	private int memPassoX, memPassoY;
	private short dirOrigem; 
	
	public RoboQueDeveVoltar(String n, int px, int py, short d, long e) {
		super(n, px, py, d);
		energia = e;
		mudaDirecao(d);
		dirOrigem = this.direcao;
	}
	
	public boolean ehDiagonal() {
		int n = direcaoAtual();
		return (n >= 45 && n < 315 && n%2 != 0 && n%45 == 0) ? true : false; 
	}

	public void move(int passos) {
		long energiaASerGasta = passos * ( (ehDiagonal()) ? 14 : 10);
		energiaASerGasta = Math.abs(energiaASerGasta);
		
		if (energiaASerGasta <= energia) {
			switch (direcaoAtual()) {
			case 0:
				moveX(+passos);
				memPassoX += passos;
				break;
			case 45:
				moveX(+passos);
				memPassoX += passos;
				moveY(+passos);
				memPassoY += passos;
				break;
			case 90:
				moveY(+passos);
				memPassoY += passos;
				break;
			case 135:
				moveY(+passos);
				memPassoY += passos;
				moveX(-passos);
				memPassoX -= passos;
				break;
			case 180:
				moveX(-passos);
				memPassoX -= passos;
				break;
			case 225:
				moveX(-passos);
				memPassoX -= passos;
				moveY(-passos);
				memPassoY -= passos;
				break;
			case 270:
				moveY(-passos);
				memPassoY -= passos;
				break;
			case 315:
				moveY(-passos);
				memPassoY -= passos;
				moveX(+passos);
				memPassoX += passos;
				break;
			}
			energia -= energiaASerGasta;
		}
	}
	
	public void mudaDirecao(short novaDir) {
		if(novaDir < 45 || novaDir > 315) 
			direcao = 0;
		
		else if(novaDir > 45 && novaDir < 135) 
			direcao = 90;
		
		else if(novaDir > 135 && novaDir < 225) 
			direcao = 180;
		
		else if(novaDir > 225 && novaDir < 315) 
			direcao = 270;
		
		else 
			direcao = novaDir;
	}
	
	public void retornaAOrigem() {
		mudaDirecao((short) 0);
		move(-memPassoX);
		
		mudaDirecao((short) 90);
		move(-memPassoY);
		
		mudaDirecao(dirOrigem);
	}
	
	public String toString() {
		String resultado = super.toString() + "\n";
		resultado = resultado + "Energia do robô:" + energia;
		return resultado;
	}
}