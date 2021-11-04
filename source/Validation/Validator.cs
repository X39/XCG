using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG.Validation
{
    public class Validator
    {
        private readonly List<IRule> _rules = new();
        private readonly HashSet<RuleKey> _ruleKeys = new();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="rule"></param>
        /// <exception cref="KeyAlreadyPresentException">Thrown if a rule is having the same <see cref="IRule.Realm"/> and <see cref="IRule.Code"/></exception>
        public void Register(IRule rule)
        {
            lock (this)
            {
                var ruleKey = new RuleKey {Realm = rule.Realm, Code = rule.Code};
                if (_ruleKeys.Contains(ruleKey))
                {
                    throw new KeyAlreadyPresentException(rule.Realm, rule.Code);
                }

                _rules.Add(rule);
                _ruleKeys.Add(ruleKey);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="realm"></param>
        /// <param name="code"></param>
        /// <param name="severity"></param>
        /// <param name="func"></param>
        /// <exception cref="KeyAlreadyPresentException">Thrown if a rule is having the same <see cref="IRule.Realm"/> and <see cref="IRule.Code"/></exception>
        public void Register(string realm, int code, ESeverity severity, Func<Parsing.Parser, IEnumerable<Hint>> func)
        {
            lock (this)
            {
                var ruleKey = new RuleKey {Realm = realm, Code = code};
                if (_ruleKeys.Contains(ruleKey))
                {
                    throw new KeyAlreadyPresentException(realm, code);
                }

                _rules.Add(new Rule {Realm = realm, Severity = severity, Code = code, ValidationFunc = func});
                _ruleKeys.Add(ruleKey);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="realm"></param>
        /// <param name="severity"></param>
        /// <param name="func"></param>
        /// <exception cref="KeyAlreadyPresentException">Thrown if a rule is having the same <see cref="IRule.Realm"/> and <see cref="IRule.Code"/></exception>
        public void Register(string realm, ESeverity severity, Func<Parsing.Parser, IEnumerable<Hint>> func)
        {
            lock (this)
            {
                var code = _rules.Where((q) => q.Realm == realm).Select((q) => q.Code).Append(0).Max() + 1;
                var ruleKey = new RuleKey {Realm = realm, Code = code};
                if (_ruleKeys.Contains(ruleKey))
                {
                    throw new KeyAlreadyPresentException(realm, code);
                }

                _rules.Add(new Rule {Realm = realm, Severity = severity, Code = code, ValidationFunc = func});
                _ruleKeys.Add(ruleKey);
            }
        }

        /// <summary>
        /// Performs the validation by evaluating every <see cref="IRule"/> registered.
        /// </summary>
        /// <param name="parser"></param>
        /// <param name="reportCallback">A callback for the <see cref="IRule"/>s evaluating to false.</param>
        /// <returns>True if no <see cref="IRule"/> with a <see cref="IRule.Severity"/> of <see cref="ESeverity.Error"/> evaluated to false.</returns>
        public bool Validate(Parsing.Parser parser, Action<IRule, Hint> reportCallback)
        {
            var success = true;
            lock (this)
            {
                foreach (var rule in _rules)
                {
                    foreach (var hint in rule.IsValid(parser))
                    {
                        if (rule.Severity == ESeverity.Error)
                        {
                            success = false;
                        }

                        reportCallback(rule, hint);
                    }
                }
            }

            return success;
        }
    }
}