class BresenhamAlgorithm
  attr_reader :xinit, :yinit, :xend, :yend, :deltax, :deltay, :eixox, :eixoy, :pks
  
  def initialize(ponto_inicial, ponto_final)
    @xinit = ponto_inicial[0]
    @yinit = ponto_inicial[1]
  
    @xend = ponto_final[0]
    @yend = ponto_final[1]
    @eixox = []
    @eixoy = []
    @pks = []
  end
 
  def self.perform(*args)
    new(*args).perform
  end

  def perform
    calcular_pontos
    imprimir_pontos
  end
  
  private
  
  def deltax
    @deltax ||= xend - xinit
  end
  
  def deltay
    @deltay ||= yend - yinit
  end
  
  def calcular_pontos
    inverter_pontos_inicial_e_final if xinit > xend && yinit > yend
 
    # Casos especiais do slide 40
    return special_case if deltay.zero? || deltax.zero? || deltax.abs == deltay.abs
    
    m = deltay.to_f / deltax.to_f
    
    if m > 0 && m < 1
     incremento_em_x
    else
      incremento_em_y
    end
  end

  def inverter_pontos_inicial_e_final
    puts '#inverteu_pontos_inicial_e_final'

    _a1, _a2 = xinit, yinit
    @xinit, @yinit = @xend, @yend
    @xend, @yend = _a1, _a2
  end

  def special_case
    if deltay.zero?
      linha_horizontal
    elsif deltax.zero?
      linha_vertical
    else
      linha_diagonal
    end
  end

  def linha_horizontal
    puts '#linha_horizontal'

    qtd_pontos = xend - xinit + 1
    qtd_pontos.times { |i| @eixox << xinit + i }
    @eixoy = Array.new(qtd_pontos, yinit)
  end

  def linha_vertical
    puts '#linha_vertical'

    qtd_pontos = yend - yinit + 1
    qtd_pontos.times { |i| @eixoy << yinit + i }
    @eixox = Array.new(qtd_pontos, xinit)
  end

  def linha_diagonal
    puts '#linha_diagonal'
    
    qtd_pontos = yend - yinit + 1
    qtd_pontos.times { |i| @eixox << xinit + i }
    qtd_pontos.times { |i| @eixoy << yinit + i }
  end

  def incremento_em_x
    puts '#incremento_em_x'
    
    x_corrente, y_corrente = xinit, yinit
    
    pk = 2*deltay - deltax

    qtd_pontos = xend - xinit

    @eixox << xinit
    @eixoy << yinit
    @pks << pk

    qtd_pontos.times do
      x_corrente += 1

      if pk < 0
        pk = pk + 2*deltay
      else
        y_corrente += 1
        pk = pk + 2*deltay - 2*deltax
      end
    
      @eixox << x_corrente
      @eixoy << y_corrente
      @pks << pk
    end
  end

  def incremento_em_y
    puts '#incremento_em_y'

    x_corrente, y_corrente = xinit, yinit
    
    pk = 2*deltax - deltay

    qtd_pontos = yend - yinit
  
    @eixox << xinit
    @eixoy << yinit
    @pks << pk

    qtd_pontos.times do
      y_corrente += 1

      if pk < 0
        pk = pk + 2*deltax
      else
        x_corrente += 1
        pk = pk + 2*deltax - 2*deltay
      end

      @eixox << x_corrente
      @eixoy << y_corrente
      @pks << pk
    end
  end

  def imprimir_pontos
    print "\n x: \t"
    eixox.each { |x| print "#{x}\t"}
    print "\n y: \t"
    eixoy.each { |y| print "#{y}\t"}
    print "\npk:\t" if pks.any?
    pks.each { |pk| print "#{pk}\t"}
    print "\n\n"
  end
end

# Ex: BresenhamAlgorithm.perform([7, 8], [15, 11])