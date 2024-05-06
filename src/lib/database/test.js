const pdb = require("./index.js")
var db  = new pdb();

async function main() {
    await db.loadDatabase();
    console.log(db.getProblemsCount())
    console.log(db.getUniqueOJNames())
}
main()
