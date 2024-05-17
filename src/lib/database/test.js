const pdb = require("./index.js")
var db  = new pdb();

async function main() {
    db.loadDatabase();
    console.log(db.getProblemsCount())
    console.log(db.getUniqueOJNames())
    // console.log(db.getProblemById('luogu-3195'))

    console.log( db.find_pre_rbook('decision_mono'))

}
main()
