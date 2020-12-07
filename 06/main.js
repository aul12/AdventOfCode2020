const fs = require('fs');

function makeSet() {
    var s = new Set()
    for (var c=0; c<26; ++c) {
        s.add(String.fromCharCode(c+97));
    }
    return s;
}

try {
    const data = fs.readFileSync('input', 'UTF-8');

    const lines = data.split(/\r?\n/);

    var count = 0;
    var answers = makeSet();
    console.log(answers)

    lines.forEach((line) => {
        if (line == "") {
            console.log("########################");
            count += answers.size
            answers = makeSet();
        } else {
            personAnswers = new Set() 
            for (let c of line) {
                personAnswers.add(c)
            }

            console.log("Person", personAnswers)
            console.log("Answers", answers)
            answers = new Set([...answers].filter(x => personAnswers.has(x)));
            console.log("intersect", answers)
        }
    });

    console.log(count)
} catch (err) {
    console.error(err);
}
