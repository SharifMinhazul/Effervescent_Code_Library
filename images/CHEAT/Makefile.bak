TeX	=	tex
CAT	=	dviconcat

PAGES	=	t1.dvi t2.dvi t3.dvi t4.dvi t5.dvi t6.dvi t7.dvi t8.dvi t9.dvi t10.dvi

cheat:	cheat.dvi

cheat.ps:	cheat.dvi
		dvips -f cheat.dvi >cheat.ps

cheat.dvi: $(PAGES)
	$(CAT) $(PAGES) > cheat.dvi

cheat.tex: psfig.tex stables.tex macros.tex

unit.tex: unit.fig
	./bin/fig2tex -m 0.5 unit.fig

angle.tex: angle.fig
	./bin/fig2tex -m 0.3 angle.fig

triangle.tex: triangle.fig
	./bin/fig2tex -m 0.8 triangle.fig

ecsher.ps: ecsher.gif
	./bin/gif2ps ecsher.gif 1.85

trig1.tex: unit.tex
trig2.tex: triangle.tex
geom.tex: angle.tex
t10.tex: ecsher.ps

t1.dvi:	t1.tex
	$(TeX) t1.tex

t2.dvi:	t2.tex
	$(TeX) t2.tex

t3.dvi:	t3.tex
	$(TeX) t3.tex

t4.dvi:	t4.tex unit.tex triangle.tex
	$(TeX) t4.tex

t5.dvi:	t5.tex
	$(TeX) t5.tex

t6.dvi:	t6.tex
	$(TeX) t6.tex

t7.dvi:	t7.tex
	$(TeX) t7.tex

t8.dvi:	t8.tex 
	$(TeX) t8.tex

t9.dvi:	t9.tex 
	$(TeX) t9.tex

t10.dvi: t10.tex
	$(TeX) t10.tex

clean:
	rm -f angle.tex triangle.tex unit.tex $(PAGES) cheat.dvi *.log *.bak cheat.ps

tar:	clean
	cd /home/seiden_bit; tar cfv cheat.tar CHEAT; mv cheat.tar CHEAT
	gzip cheat.tar

depend:
	./bin/makedepend t?.tex t10.tex

# DO NOT DELETE THIS LINE -- make depend depends on it.

t1.dvi:  cheat.tex sums.tex ids2.tex
t2.dvi:  cheat.tex ids3.tex trees.tex recur1.tex recur2.tex recur3.tex
t3.dvi:  cheat.tex misc.tex prob.tex prob2.tex
t4.dvi:  cheat.tex trig1.tex matrix.tex trig2.tex hyper.tex table.tex quote4.tex
t5.dvi:  cheat.tex number.tex graph.tex graph2.tex geom.tex quote1.tex
t6.dvi:  cheat.tex pi.tex calc.tex partial.tex quote3.tex
t7.dvi:  cheat.tex calc2.tex
t8.dvi:  cheat.tex calc3.tex finite.tex fact1.tex fact2.tex
t9.dvi:  cheat.tex series1.tex series3.tex quote2.tex
t10.dvi:  cheat.tex series2.tex series4.tex stieltjes.tex magic.tex cramers.tex fib1.tex fib2.tex
