#include <skypat/skypat.h>

#include <parserGen/RuleParser.hpp>

SKYPAT_F(RuleParser_unittest, create_delete)
{
    ByteBuffer* buffer = new_ByteBuffer(5);
    set_ByteBuffer(buffer, 0, "Test", 5);
    RuleParser ruleParser(&buffer, 1);

    Pass* pass = ruleParser.getPass();
    RuleBuffer* ruleBuffer = ruleParser.getRuleBuffer();
    EXPECT_EQ(pass->input, &buffer);
    EXPECT_EQ(pass->input_count, 1);
    EXPECT_EQ(*pass->output, (Buffer*)ruleBuffer);
    EXPECT_EQ(pass->output_count, 1);
    pass->free(&pass);
    EXPECT_EQ(pass, NULL);
}

SKYPAT_F(RuleParser_unittest, parse_rule)
{
    ByteBuffer* buffer = new_ByteBuffer(38);
    set_ByteBuffer(buffer, 0, "Test: test1 test2? test3\nTest2: test4", 38);
    RuleParser ruleParser(&buffer, 1);

    Pass* pass = ruleParser.getPass();
    pass->run(pass);
    RuleBuffer* ruleBuffer = ruleParser.getRuleBuffer();
    Rule& testRule = ruleBuffer->getRule("Test", 0);
    EXPECT_EQ(testRule.target, "Test");
    EXPECT_EQ(testRule.elements.size(), 3);
    EXPECT_EQ(testRule.elements.at(0).name, "test1");
    EXPECT_FALSE(testRule.elements.at(0).isOptional);
    EXPECT_EQ(testRule.elements.at(1).name, "test2");
    EXPECT_TRUE(testRule.elements.at(1).isOptional);
    EXPECT_EQ(testRule.elements.at(2).name, "test3");
    EXPECT_FALSE(testRule.elements.at(2).isOptional);
    testRule = ruleBuffer->getRule("Test2", 0);
    EXPECT_EQ(testRule.target, "Test2");
    EXPECT_EQ(testRule.elements.size(), 1);
    EXPECT_EQ(testRule.elements.at(0).name, "test4");
    EXPECT_FALSE(testRule.elements.at(0).isOptional);
    pass->free(&pass);
}
