CREATE TABLE Ator(
                 coda integer,
                 nomeart varchar(25),
                 nomereal varchar(25),
                 nacionalidade varchar(25),
                 sexo char,
                 indicacoesoscar integer, 
                 num_oscar integer,
  PRIMARY KEY (coda)
) ENGINE=InnoDB;
                 
CREATE TABLE Filme(
                   codf integer,
                   nome varchar(20),
                   ano integer,
                   orcamento float, 
                   tempo float,
  PRIMARY KEY (codf)
) ENGINE=InnoDB;
                  
create table Personagem(
                       coda integer, 
                       codf integer,
                       personagem varchar(25),
                       cache float,
  PRIMARY KEY (coda, codf),
  FOREIGN KEY (coda) REFERENCES Ator(coda),
  FOREIGN KEY (codf) REFERENCES Filme(codf)
) ENGINE=InnoDB;

INSERT INTO Ator(coda, nomeart, nomereal, nacionalidade, sexo, indicacoesoscar, num_oscar) 
VALUES (1, 'Demi Moore', 'Maria Da Silva', 'USA', 'F', 0, 0),
       (2, 'Brad Pitt', 'Joao Paulo', 'USA', 'F', 1, 0),
       (3, 'Dustin Hoffman', 'Dustin Hoffman', 'USA', 'M', 2, 0),
       (4, 'Jessica Lange', 'Jessica Lange', 'USA', 'F', 4, 2),
       (5, 'Sonia Braga', 'Sonia Braga', 'Brasil', 'F', 0, 0);
        
INSERT INTO Filme(codf, nome, ano, orcamento, tempo)
VALUES (1, 'A Jurada', 1996, 1000000, 18),
       (2, 'A Letra Escarlate', 1995, 10000000, 24),
       (3, 'Seven', 1995, 1500000, 20),
       (4, 'Tootsie', 1982, 50000, 16),
       (5, 'Tieta', 1995, 200000, 18);
       
INSERT INTO Personagem(coda, codf, personagem, cache)
VALUES (1, 1, 'Mary', 3000),
       (1, 2, 'Sandy', 5000),
       (2, 3, 'John', 5000),
       (3, 4, 'Mary', 1000),
       (4, 4, 'Tootsie', 2000),
       (5, 5, 'Tieta', 500);

/* Ex.01
   - Altera o sexo do ator Brad Pitt para M */
UPDATE Ator SET sexo='M' where nomeart='Brad Pitt';

/* Ex.02
   -  Aumenta o cachê dos atores em 10% */
UPDATE Personagem SET cache = cache + cache*0.10;

/* Ex.03
   - Não é possível excluir o filme Tieta pois ele é referenciado pela tabela de personagens, e não colocamos a exclusão em cascata, portanto, 
     se excluíssemos este filme, teríamos uma referência na tabela de personagens a um filme que não existe mais, o que não pode ocorrer. */
DELETE from Filme WHERE nome='Tieta';

/* Ex.04
   - Neste caso conseguimos excluir sem problemas, pois a tabela Personagem é a que faz referência a outras duas, Ator e Filme, porém não é referenciada por ninguém.
   - O fato de um Personagem não existir, não interfere na existência do ator e do filme, logo, não temos problemas. */
Delete FROM Personagem WHERE personagem='Tootsie';