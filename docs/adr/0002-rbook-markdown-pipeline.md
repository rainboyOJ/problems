# Reuse the rbook Markdown pipeline for problem statements

Problem statements will be rendered on the server with an adapted version of the existing rbook Markdown pipeline. The corpus relies heavily on mathematical formulas and also contains images, tables, and a small number of container blocks, so a plain Markdown parser would silently degrade real content. The first version will guarantee the common statement features and preserve unsupported advanced diagram or pseudocode fences as readable code instead of making those optional extensions a runtime requirement.
