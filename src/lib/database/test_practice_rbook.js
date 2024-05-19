const pdb = require("./index.js")
var db  = new pdb();

async function main() {
    db.loadDatabase();
    console.log(db.getProblemsCount())
    console.log(db.getUniqueOJNames())
    // console.log(db.getProblemById('luogu-3195'))

    console.log( db.solutions_has_practice_rbook('ball_and_box'))

}
main()
