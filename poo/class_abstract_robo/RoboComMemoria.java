package JavaProjects.class_abstract_robo;

public class RoboComMemoria extends RoboAbstrato {
	private int memPassoX, memPassoY;
	private short dirOrigem; 
	
	public RoboComMemoria(String n, int px, int py, short d) {
		super(n, px, py, d);
		dirOrigem = d;
	}

	public void move(int passos) {
		switch (direcaoAtual()) {
		case 0:
			moveX(+passos);
			memPassoX += passos;
			break;
		case 90:
			moveY(+passos);
			memPassoY += passos;
			break;
		case 180:
			moveX(-passos);
			memPassoX -= passos;
			break;
		case 270:
			moveY(-passos);
			memPassoY -= passos;
			break;
		}
	}
	
	public void retornaAOrigem() {
		mudaDirecao((short) 0);
		move(-memPassoX);
		
		mudaDirecao((short) 90);
		move(-memPassoY);
		
		mudaDirecao(dirOrigem);
	}
}