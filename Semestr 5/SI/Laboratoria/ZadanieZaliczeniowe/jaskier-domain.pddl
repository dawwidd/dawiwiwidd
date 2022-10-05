(define
    (domain jaskier)
    (:requirements :adl)
    (:types miasto kamien)
    (:predicates
        (niedostepna ?miejscowosc)
        (ma ?kamien)
        (polaczone ?miejscowosc1 ?miejscowosc2)
        (jaskier-w ?miejscowosc)
        (miejsce-wymiany ?gdzie ?czego ?naco)
    )
    (:action wymien
        :parameters (?gdzie - miasto ?co - kamien ?naco - kamien)
        :precondition
        (and
            (jaskier-w ?gdzie)
            (ma ?co)
            (miejsce-wymiany ?gdzie ?co ?naco)
        )
        :effect
        (and
            (ma ?naco)
            (not (ma ?co))
            (niedostepna ?gdzie)
        )
    )
    (:action przejdz
        :parameters (?skad - miasto ?dokad - miasto)
        :precondition
        (and
            (or (polaczone ?skad ?dokad) (polaczone ?dokad ?skad))
            (not (niedostepna ?dokad))
            (jaskier-w ?skad)
        )
        :effect
        (and
            (jaskier-w ?dokad)
            (not (jaskier-w ?skad))
        )
    )
)