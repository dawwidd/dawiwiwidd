(define (problem jaskier)
	(:domain Jaskier)
	(:objects
		aon gart ezberg filian dagrod bama cerwa - miasto
        rubin jadeit szafir agat opal - kamien
	)
	(:init
        (polaczone aon dagrod)
        (polaczone aon gart)
        (polaczone bama cerwa)
        (polaczone bama dagrod)
        (polaczone cerwa filian)
        (polaczone dagrod filian)
        (polaczone ezberg filian)
        (polaczone ezberg gart)
        

        (miejsce-wymiany bama opal szafir)
        (miejsce-wymiany cerwa opal agat)
        (miejsce-wymiany dagrod rubin opal)
        (miejsce-wymiany ezberg agat szafir)
        (miejsce-wymiany filian szafir jadeit)
        (miejsce-wymiany gart szafir opal)

        (jaskier-w dagrod)
        (ma rubin)
	)
	(:goal
	(and		
        (jaskier-w aon)
        (ma jadeit)
	)
	)

)