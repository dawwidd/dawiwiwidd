    // DEBUG = true powoduje wypisanie BARDZO dużej
    // ilości informacji, dzięki którym można odczytać
    // przebieg działania (np. jak dopasowano zmienne 
    // albo na którym warunku odrzucono regułę)
     
    // Reguły ustawiamy w zmiennej rules (linia ok. 164)
     
    // Fakty ustawiamy w zmiennej mem (linia ok. 175)
     
    let DEBUG = false
     
    function parseResults(arr) {
        const a = arr.map(str => {
     
            const a = str.split('(')
            const n = a[1].match(/[\$\?][0-9]+/g) || []
            return { variable: a[0], string: a[1].replace(')', ''), names: n }
     
        })
        return (mem) => {
            for (const t of a) {
     
                if (DEBUG) {
                    console.log('Akcja:')
                    if (typeof process === 'object') // if Node.js
                        console.log(t)
                    else
                        console.log(JSON.stringify(t))
                }
     
     
                mem[t.variable] = t.string
                for (const x of t.names) {
                    //console.log(mem[t.variable])
                    mem[t.variable] = mem[t.variable].split(x).join(mem[x]) //split(s).join(x) to jest replaceAll(s, x)
                }
     
                if (DEBUG) {
                    console.log('Pamięć:')
                    if (typeof process === 'object') // if Node.js
                        console.log(mem)
                    else
                        console.log(JSON.stringify(mem))
                }
            }
        }
    }
     
    function parseCondition(arr) {
        const a = arr.map(str => {
            if (/\!\w*=/.test(str)) {
                return { type: '!=', operands: str.split(/\!\w*=/).map(x => x.trim()) }
            } else if (/=/.test(str)) {
                return { type: '=', operands: str.split('=').map(x => x.trim()) }
            } else {
                const a = str.split('(')
                const n = a[1].match(/([\$\?][0-9]+)|[A-Za-z]/g)
                let r = n.map(x => {
                    switch (x[0]) {
                        case '$':
                            return '#'
                        case '?':
                            return '(.)'
                        default:
                            return x;
                    }
                }).reduce((p, c) => p + c)
     
                const regexps = []
                for (let i = 0; i < 6; i++) {
                    let a = r
                    a = a.replace('#', `(.{${i}})`)
                    for (let j = 0; j < 6; j++) {
                        let b = a
                        b = b.replace('#', `(.{${j}})`)
                        for (let k = 0; k < 6; k++) {
                            let c = b
                            c = c.replace('#', `(.{${k}})`)
                            for (let l = 0; l < 6; l++) {
                                let d = c
                                d = d.replace('#', `(.{${l}})`)
                                if (regexps.indexOf(d) == -1)
                                    regexps.push(d)
                            }
                        }
                    }
                }
                //console.log(r)
                //console.log(regexps)
                //console.log(r)
                return { type: 'match', variable: a[0], names: n.filter(x => /[\$\?]/.test(x)), regexps: regexps.map(r => new RegExp('^' + r + '$')) }
            }
        })
        return (mem) => {
            return tryMatch(a, mem)
        }
    }
    function tryMatch(a, mem) {
        //console.log(a)
        for (let it = 0; it < a.length; it++) {
            const t = a[it]
     
            if (DEBUG) {
                console.log('Pamięć:')
                if (typeof process === 'object') // if Node.js
                    console.log(mem)
                else
                    console.log(JSON.stringify(mem))
                console.log('Warunek:')
                if (typeof process === 'object') // if Node.js
                    console.log(t)
                else
                    console.log(JSON.stringify(t))
            }
     
     
            switch (t.type) {
                case '!=':
                    if (mem[t.operands[0]] == mem[t.operands[1]])
                        return false;
                    break;
                case '=':
                    if (mem[t.operands[0]] != mem[t.operands[1]])
                        return false;
                    break;
                case 'match':
                    {
                        for (const r of t.regexps) {
                            const memCopy = { ...mem }
                            const m = memCopy[t.variable].match(r)
                            //console.log('Test regex', r)
                            if(m) {
                                m.splice(1).forEach((e, i) => {
                                    memCopy[t.names[i]] = e
                                })
                                if (tryMatch(a.slice(it + 1), memCopy)) {
                                    for (const key in memCopy) {
                                        mem[key] = memCopy[key]
                                    }
                                    //console.log('Dopasowałem')
                                    return true
                                }
                            }
                        }
                        //console.log('Nie dopasowałem')
                        return false
                    }
                    break;
            }
        }
        //console.log('Kurła')
        return true
    }
     
     
    function parseRule(str) {
        let [condition, apply] = str
            .replace('IF', '')
            .split('THEN')
            .map(s => s.split('AND').map(x => x.trim()))
        return { condition: parseCondition(condition), apply: parseResults(apply) }
    }
     
    // TU MODYFIKOWAĆ
     
    let mem = { p: 'def', r: 'afcd', q: '', w: ''}
     
    const rules = [
        'IF p(?1$1)    AND r(?2$2)   AND ?1!=?2  AND q($3) THEN r($2) AND q($3?2)',
        'IF p(?1$1) AND r(?2$2)   AND ?1!=?2  AND q($3)   AND w($4)   THEN p($1) AND r($3$2) AND q() AND w($4?1)',
        'IF p(?1$1) AND r() AND q($2) THEN p($1) AND r($2) AND q()'
    ].map(rule => parseRule(rule))
     
    //KONIEC
     
     
    while (true) {
        const next = rules.map((rule, i) => {
            const memCopy = { ...mem }
            if (DEBUG)
                console.log('Sprawdzam warunek reguły: ', i + 1)
            return { R: i, active: rule.condition(memCopy), mem: memCopy }
        })
        const active = next.filter(x => x.active).map(x => x.R + 1)
        console.log('Reguły aktywne: ', active)
        if (active.length == 0)
            break;
     
        console.log('Reguła odpalona: ', active[0])
        mem = next[active[0] - 1].mem
        rules[active[0] - 1].apply(mem)
        mem = Object.keys(mem)
            .filter(key => !/[\$\?]/.test(key))
            .reduce((obj, key) => {
                obj[key] = mem[key];
                return obj;
            }, {})
     
     
        if (typeof process === 'object') // if Node.js
            console.log('Fakty: ', mem)
        else
            console.log('Fakty: ', JSON.stringify(mem))
    }