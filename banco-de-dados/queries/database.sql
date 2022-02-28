create table ator(coda integer, nomeart varchar(20), nomereal varchar(20), sexo char(2), 
idade integer, indicacoes_oscar integer, oscar integer, primary key(coda)) ENGINE= INNODB;


create table filme(codf integer, nome varchar(20), ano integer, tempo integer, primary key(codf))
ENGINE= INNODB;

CREATE TABLE personagem (coda integer, codf integer, personagem varchar(12), cache real, primary key(coda, codf)) ENGINE= INNODB;

ALTER TABLE personagem ADD foreign key (coda) references ator(coda);
ALTER TABLE personagem ADD foreign key (codf) references filme(codf);


insert into ator values (1, 'demi moore', 'maria da silva','f', 32, 0, 0);
insert into ator values (2, 'brad pitt', 'joao paulo','m', 28, 1, 0);
insert into ator values (3, 'dustin hoffman', 'dustin','m', 46, 2, 0);
insert into ator values (4, 'jessica lange', 'jessica','f', 42, 4, 2);
insert into ator values (5, 'sonia braga', 'sonia braga','f', 60, 0, 0);



insert into filme values(1, 'a jurada', 1996, 18);
insert into filme values(2, 'a letra escarlate', 1995, 24);
insert into filme values(3, 'seven', 1995, 20);
insert into filme values(4, 'tootsie', 1982, 16);
insert into filme values(5, 'tieta', 1995, 18);


insert into personagem values (1,1, 'mary', 3000);
insert into personagem values (1,2, 'sandy', 5000);
insert into personagem values (2,3, 'john', 5000);
insert into personagem values (3,4, 'mary', 10000);
insert into personagem values (4,4, 'tootsie', 2000);
insert into personagem values (5,5, 'tieta', 500);
